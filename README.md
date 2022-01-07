
> ## After installing this template
> This is just a template to start working in a C++ project. It includes basic folder
> structure using CMake and Catch2 test framework. It also included some basic Conan files
> to grab dependencies and start working with CIs.
> 
> Search for TODO comments to apply the changes that are required to your specific project
> and spend some time having a look to '.github/workflows' files to adjust them to your needs
> (usually you can just remove all files starting with underscore).
> 
> Most of this template is designed to work together with 'https://github.com/jgsogo/conan-recipes'
> repository, you might need to move some of those files to your own organization.
> 
> In order to work with `jgsogo/conan-recipes` there are two secrets expected in this repository:
> * `APP_RECIPES_APP_ID`:  
> * `APP_RECIPES_PRIVATE_KEY`:
> 
> These secreats are used by `.github/workflows/published_release.yml` to open a PR to
> `jgsogo/conan-recipes` when a new release is published in this repository.
>

<!-- TODO: Use your repository here -->
[![Build and tests](https://github.com/jgsogo/template-cpp-project/actions/workflows/ci.yml/badge.svg?event=push)](https://github.com/jgsogo/template-cpp-project/actions/workflows/ci.yml)
[![Build and tests](https://github.com/jgsogo/template-cpp-project/actions/workflows/conan_package.yml/badge.svg?event=push)](https://github.com/jgsogo/template-cpp-project/actions/workflows/ci.yml)

## Consume the library

This library is available as a Conan package in my personal remote repository. To consume it, you just
need to add the remote:


<!-- TODO: Use your library/version here -->
```
conan remote add sogo https://sogo.jfrog.io/artifactory/api/conan/conan-center
conan install <library_name>/<library_version>@jgsogo/stable
```

Or, add the remote and list the reference in your `conanfile.txt/py` file.


## Build and run locally

```
mkdir cmake-build-xxxx && cd cmake-build-xxxx
```

```
conan lock create --profile:host=../.conan/profiles/cpp20 --profile:build=default --lockfile=../lockfile.json --lockfile-out=lockfile.json --name=cpp-project --version=0.1 ../conanfile.txt --build --update
```

```
conan install --lockfile=lockfile.json ../conanfile.txt --build=missing --generator=virtualenv
```

## Update dependencies

```
conan lock create --name=composite --version=0.1 --base --lockfile-out lockfile.json conanfile.txt --build --profile:host=.conan/profiles/cpp20 --profile:build=default
```
