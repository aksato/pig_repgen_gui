from conan import ConanFile


class MesonQtInjaConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PkgConfigDeps", "MesonToolchain"

    def requirements(self):
        self.requires("qt/5.15.14")
        self.requires("inja/3.4.0")
        self.requires("sqlite_orm/1.9")
        self.requires("sqlite3/3.46.1", override=True)

    def configure(self):
        self.options["qt/*"].shared = True
