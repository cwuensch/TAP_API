FROM i386/ubuntu:latest

RUN apt-get update && apt-get install -y make wget

ARG FBLib=MergeIntoMC
ENV FBLib=${FBLib}
ENV PATH=/opt/crosstool/bin:/opt/crosstool/mipsel-linux-uclibc/bin:${PATH}

ADD crosstool_linux.tar.gz /opt/crosstool/
COPY TMS /tapapi/TMS/

RUN mv /tapapi/TMS/libuuid.a /opt/crosstool/lib/ \
 && mkdir -p /opt/crosstool/include/uuid \
 && mv /tapapi/TMS/include/uuid/uuid.h /opt/crosstool/include/uuid/

RUN mv /tapapi/TMS/JailBreak /opt/crosstool/bin/ \
 && sed -i "s/JailBreak.exe/JailBreak/" /tapapi/TMS/include/tool.mk

VOLUME /tap
WORKDIR /tap

ADD https://github.com/cwuensch/FireBirdLib/raw/${FBLib}/libFireBird.h /tapapi/TMS/include/
ADD https://github.com/cwuensch/FireBirdLib/raw/${FBLib}/libFireBird.a /opt/crosstool/lib/

RUN ["/bin/sh", "-c", "echo \"#!/bin/sh\nwget https://github.com/cwuensch/FireBirdLib/raw/\\${FBLib}/libFireBird.h -O /tapapi/TMS/include/libFireBird.h\nwget https://github.com/cwuensch/FireBirdLib/raw/\\${FBLib}/libFireBird.a -O /opt/crosstool/lib/libFireBird.a\nif [ -n \\\"\\$1\\\" ] ; then\n  /bin/bash -c \\\"\\$@\\\"\nelse\n  /bin/bash\nfi\" > /entrypoint.sh && chmod u+x /entrypoint.sh"]

ENTRYPOINT ["/entrypoint.sh"]
