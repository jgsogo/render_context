
[![Build and tests](https://github.com/jgsogo/render_context/actions/workflows/ci.yml/badge.svg?event=push)](https://github.com/jgsogo/render_context/actions/workflows/ci.yml)
[![Build and tests](https://github.com/jgsogo/render_context/actions/workflows/conan_package.yml/badge.svg?event=push)](https://github.com/jgsogo/render_context/actions/workflows/ci.yml)

## Consume the library

This library is available as a Conan package in my personal remote repository. To consume it, you just
need to add the remote:


```
conan remote add sogo https://sogo.jfrog.io/artifactory/api/conan/conan-center
conan install render_context/0.1.0@jgsogo/stable
```

Or, add the remote and list the reference in your `conanfile.txt/py` file.


## Build and run locally

```
mkdir cmake-build-xxxx && cd cmake-build-xxxx
```

```
conan lock create --profile:host=../.conan/profiles/cpp20 --profile:build=default --lockfile=../lockfile.json --lockfile-out=lockfile.json --name=render_context --version=0.1 ../conanfile.txt --build --update
```

```
conan install --lockfile=lockfile.json ../conanfile.txt --build=missing --generator=virtualenv
```

## Update dependencies

```
conan lock create --name=render_context --version=0.1 --base --lockfile-out lockfile.json conanfile.txt --build --profile:host=.conan/profiles/cpp20 --profile:build=default
```
