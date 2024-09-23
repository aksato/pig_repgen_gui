project('mesonqtinja', 'cpp', default_options: ['cpp_std=c++17'])

qt5_mod = import('qt5')
qt5widgets = dependency('qt5', modules: 'Widgets')
qt5core = dependency('qt5', modules: 'Core')
qt5gui = dependency('qt5', modules: 'Gui')

# Add Inja as a subproject dependency
inja_dep = dependency('inja')

# Add SQLite ORM as a subproject dependency
sqlite_orm_dep = dependency('sqlite_orm')

processed = qt5_mod.preprocess(
  moc_headers: 'mainwindow.h',
  ui_files: 'mainwindow.ui',
  qresources: 'resources.qrc',
)

q5exe = executable(
  'mesonqtinja',
  sources: ['main.cpp', 'db.cpp', 'repgen/repgen.cpp', 'mainwindow.cpp', processed],
  dependencies: [qt5widgets, qt5core, qt5gui, inja_dep, sqlite_orm_dep],
)