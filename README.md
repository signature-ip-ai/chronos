# Cycle Accurate SystemC Translator Libraries (chronos)

## Getting started
Install conan 2.x in your system.

```
$ pip3 install conan --user
$ conan --version
Conan version 2.x.x
$
```

Setup a default conan profile (one-time setup)

```
$ conan profile detect
detect_api: Found gcc 8
detect_api: gcc>=5, using the major as version
detect_api: gcc C++ standard library: libstdc++11

Detected profile:
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=gnu14
compiler.libcxx=libstdc++11
compiler.version=8
os=Linux

WARN: This profile is a guess of your environment, please check it.
WARN: The output of this command is not guaranteed to be stable and can change in future Conan versions.
WARN: Use your own profile files for stability.
Saving detected profile to ~/.conan2/profiles/default
```

Open ~/.conan2/profiles/default and update the cppstd to "17" (one-time setup)

```
$ conan profile show
Host profile:
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=17
compiler.libcxx=libstdc++11
compiler.version=8
os=Linux
[conf]


Build profile:
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=17
compiler.libcxx=libstdc++11
compiler.version=8
os=Linux
[conf]
```

Update _**core.cache:storage_path**_ to your own workspace directory to avoid flooding the home with conan dependencies (one-time setup)(optional)

```
$echo "\ncore.cache:storage_path = [your preferred cache storage path]" >> ~/.conan2/global.conf
```

To confirm

```
$conan config show core.cache:storage_path
core.cache:storage_path: [your preferred cache storage path]
```

## Building the libraries and running tests
After cloning the repository, go inside "chronos/amba_chi" directory and run _**conan install**_.

```
$ cd chronos/amba_chi
$ conan install . --build missing
```

To build the executable and run tests

```
$ conan build . && conan export-pkg .
```
