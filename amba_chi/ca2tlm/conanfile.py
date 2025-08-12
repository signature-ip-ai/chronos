#!/bin/env python3

import os
import tarfile

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain


class chica2tlm(ConanFile):
    name = "chica2tlm"
    version = "1.0"
    systemc_version = "2.3.4"
    spdlog_version = "1.15.1"
    cmake_version = "3.31.6"

    # Optional metadata
    license = ""
    author = ""
    url = ""
    description = ""
    topics = ("", "", "")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }

    default_options = {
        "shared": False,
        "fPIC": True,

        f"systemc/{systemc_version}:fPIC": True,
        f"systemc/{systemc_version}:shared": False,
        f"systemc/{systemc_version}:enable_pthreads": False,
        f"systemc/{systemc_version}:enable_assertions": True,
        f"systemc/{systemc_version}:disable_virtual_bind": False,
        f"systemc/{systemc_version}:disable_async_updates": False,
        f"systemc/{systemc_version}:disable_copyright_msg": True,
        f"systemc/{systemc_version}:enable_phase_callbacks": True,
        f"systemc/{systemc_version}:enable_phase_callbacks_tracing": False,
        f"systemc/{systemc_version}:enable_immediate_self_notifications": False,

        f"spdlog/{spdlog_version}:fPIC": True,
        f"spdlog/{spdlog_version}:shared": False,
        f"spdlog/{spdlog_version}:header_only": False,
        f"spdlog/{spdlog_version}:use_std_fmt": False,
        f"spdlog/{spdlog_version}:no_exceptions": True
    }

    exports_sources = "CMakeLists.txt", "src/*", "include/*"


    def config_options(self):
        if self.settings.os == "Windows": #pylint: disable=no-member
            del self.options.fPIC


    def layout(self):
        cmake_layout(self)


    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()


    def requirements(self):
        self.requires(f"systemc/{self.systemc_version}")
        self.requires(f"spdlog/{self.spdlog_version}")


    def build_requirements(self):
        self.tool_requires(f"cmake/{self.cmake_version}") #pylint: disable=not-callable


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()

        tarball_package = os.path.join(self.build_folder, f"{self.name}.tgz")

        with tarfile.open(tarball_package, "w:gz") as tar:
            tar.add(name=self.package_folder, arcname=self.name)

        self.output.info(f"Tarball package can be found at: {tarball_package}")

    def package_info(self):
        self.cpp_info.libs = [f"{self.name}"]
