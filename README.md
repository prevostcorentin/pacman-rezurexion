#Description

A more strategical implementation of Pac-Man

#Clone

```
git clone --recursive https://bitbucket.org/yodice/pacman-rezurexion
```

#Compiling

Compiling debug and release target without dependencies:
```
make dependencies debug-target release-target
```

It is impossible with a Makefile to implement cross-platform directory creation (damn backslashes ...).
Merely all Makefile rules will pass on Windows except those with directory creation/moving.

Compilation by hand is not really difficult to figure out once you know that and understand makefiles.

If you don't want to bother yourself with compilation details try a hand at Code::Blocks or CodeLite.
