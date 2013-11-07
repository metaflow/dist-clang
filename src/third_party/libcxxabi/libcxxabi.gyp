{
  'includes': [
    '../../build/configs.gypi',
  ],

  'targets': [
    {
      'target_name': 'c++abi',
      'type': 'shared_library',
      'dependencies': [
        '../libcxx/libcxx.gyp:c++-bootstrap',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          'include',
        ],
      },
      'cflags': [
        '-std=c++11',
        '-stdlib=libc++',
        '-fPIC',
        '-fstrict-aliasing',
        '-Wstrict-aliasing=2',
        '-Wsign-conversion',
        '-Wshadow',
        '-Wconversion',
        '-Wunused-variable',
        '-Wmissing-field-initializers',
        '-Wchar-subscripts',
        '-Wmismatched-tags',
        '-Wmissing-braces',
        '-Wshorten-64-to-32',
        '-Wsign-compare',
        '-Wstrict-overflow=4',
        '-Wunused-parameter',
        '-Wnewline-eof',
      ],
      'ldflags': [
        '-nodefaultlibs',
        '-lpthread',
        '-lrt',
        '-lc',
        '-lstdc++',
      ],
      'include_dirs': [
        'include',
      ],
      'sources': [
        'src/abort_message.cpp',
        'src/abort_message.h',
        'src/cxa_aux_runtime.cpp',
        'src/cxa_default_handlers.cpp',
        'src/cxa_demangle.cpp',
        'src/cxa_exception.cpp',
        'src/cxa_exception.hpp',
        'src/cxa_exception_storage.cpp',
        'src/cxa_guard.cpp',
        'src/cxa_handlers.cpp',
        'src/cxa_handlers.hpp',
        'src/cxa_new_delete.cpp',
        'src/cxa_personality.cpp',
        'src/cxa_unexpected.cpp',
        'src/cxa_vector.cpp',
        'src/cxa_virtual.cpp',
        'src/exception.cpp',
        'src/fallback_malloc.ipp',
        'src/private_typeinfo.cpp',
        'src/private_typeinfo.h',
        'src/stdexcept.cpp',
        'src/typeinfo.cpp',
      ],
    },
  ],
}