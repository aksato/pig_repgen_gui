project('mesonqtinja', 'cpp', default_options: ['cpp_std=c++17'])

qt5_mod = import('qt5')
qt5widgets = dependency('qt5', modules : 'Widgets')
qt5core = dependency('qt5', modules : 'Core')
qt5gui = dependency('qt5', modules : 'Gui')

# Add Inja as a subproject dependency
inja_proj = subproject('inja')
inja_dep = inja_proj.get_variable('inja_dep')

processed = qt5_mod.preprocess(
  moc_headers : 'mainwindow.h', 
  ui_files    : 'mainwindow.ui',
  qresources  : 'resources.qrc',
)

q5exe = executable('mesonqtinja',
  sources     : ['main.cpp',
                 'mainwindow.cpp',
                 processed],
  dependencies: [qt5widgets, qt5core, qt5gui, inja_dep]  # Link Inja library
)
