#!/bin/env python3
import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain
from conan.tools.build import can_run


class amabchicast_tests(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    systemc_version = "3.0.1"
    gtest_version = "1.16.0"
    spdlog_version = "1.15.3"
    cmake_version = "3.31.6"
    ambachicast_version = "1.0"

    default_options = {
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
        f"spdlog/{spdlog_version}:no_exceptions": True,

        f"gtest/{gtest_version}:shared": False,
        f"gtest/{gtest_version}:build_gmock": True,
        f"gtest/{gtest_version}:hide_symbols": False,
        f"gtest/{gtest_version}:disable_pthreads": True
    }


    def requirements(self):
        self.requires(f"systemc/{self.systemc_version}")
        self.requires(f"gtest/{self.gtest_version}")
        self.requires(f"spdlog/{self.spdlog_version}")
        self.requires(f"ambachicast/{self.ambachicast_version}")


    def build_requirements(self):
        self.tool_requires(f"cmake/{self.cmake_version}") #pylint: disable=not-callable


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def layout(self):
        cmake_layout(self)


    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()


    def test(self):
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "RnIfxAdapterTests")
            self.run(cmd, env="conanrun")

            cmd = os.path.join(self.cpp.build.bindir, "SnIfxAdapterTests")
            self.run(cmd, env="conanrun")
