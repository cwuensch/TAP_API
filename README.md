# TAP_API
Topfield TAP creation API, modifications by Firebird and me

Place source code into the folder tap and mount it into the volume to /tap.

Sample usage:
-------------
```
docker run --rm -v `pwd`/tap:/tap --env FBLib="MergeIntoMC" --workdir "/tap/MovieCutter/source" cwuensch/tmsbuild:FBLib "cd /tap/MovieCutter/source && make"

docker run --rm -v `pwd`/tap:/tap --env FBLib="MergeIntoMC" -it cwuensch/tmsbuild:FBLib
```

Recent FireBirdLib will get downloaded from specified branch within the container.

Possible branches for FBLib are:

- MergeIntoMC: CW special branch with all recent changes from master applied (default)
- FBLib_MC: CW special branch as used for MC 3.6 (static non-UTF fonts, static images, absolute paths instead ConvertPath)
- master: Original FBLib as published by FireBird
- CW_neu: Original FBLib with some special changes applied

```
docker build --build-arg FBLib="MergeIntoMC" -t "tmsbuild" .
```
