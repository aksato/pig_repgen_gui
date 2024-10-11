from conan import ConanFile
from conan.tools.cmake import cmake_layout


class MesonQtInjaConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sqlitecpp/3.3.2")
        self.requires("qt/5.15.14")

    def configure(self):
        self.options["qt/*"].shared = True

    def layout(self):
        cmake_layout(self)
