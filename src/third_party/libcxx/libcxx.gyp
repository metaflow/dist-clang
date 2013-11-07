{
  'includes': [
    '../../build/configs.gypi',
  ],

  'targets': [
    {
      'target_name': 'c++-bootstrap',
      'type': 'shared_library',
      'direct_dependent_settings': {
        'include_dirs': [
          'include',
        ],
      },
      'defines': [
        'LIBSTDCXX',
        '__GLIBCXX__',
        '_LIBCPP_NO_EXCEPTIONS',
        'cxx_EXPORTS',
      ],
      'cflags': [
        '-O3',
        '-std=c++11',
        '-nostdinc++',
        '-fPIC',
        '-fno-exceptions',
        '-pedantic',
        '-Wall',
        '-W',
        '-Wno-unused-parameter',
        '-Wwrite-strings',
        '-Wno-long-long',
        '-Wno-error',
      ],
      'cflags!': [
        '-O0',  # libc++.so loses |~basic_string()| with this flag.
      ],
      'ldflags': [
        '-nodefaultlibs',
        '-lpthread',
        '-lc',
        '-lm',
        '-lrt',
        '-lgcc_s',
        '-lstdc++',
      ],
      'include_dirs': [
        'include',
        '<(INTERMEDIATE_DIR)',
      ],
      'variables': {
        # this list is also hardcoded in 'copy_abi_headers.py'.
        'abi_headers': [
          '<(INTERMEDIATE_DIR)/bits/c++config.h',
          '<(INTERMEDIATE_DIR)/bits/cpu_defines.h',
          '<(INTERMEDIATE_DIR)/bits/cxxabi_forced.h',
          '<(INTERMEDIATE_DIR)/bits/cxxabi_tweaks.h',
          '<(INTERMEDIATE_DIR)/bits/os_defines.h',
          '<(INTERMEDIATE_DIR)/cxxabi.h',
        ],
      },
      'sources': [
        '<@(abi_headers)',
        'src/algorithm.cpp',
        'src/bind.cpp',
        'src/chrono.cpp',
        'src/condition_variable.cpp',
        'src/debug.cpp',
        'src/exception.cpp',
        'src/future.cpp',
        'src/hash.cpp',
        'src/ios.cpp',
        'src/iostream.cpp',
        'src/locale.cpp',
        'src/memory.cpp',
        'src/mutex.cpp',
        'src/new.cpp',
        'src/optional.cpp',
        'src/random.cpp',
        'src/regex.cpp',
        'src/shared_mutex.cpp',
        'src/stdexcept.cpp',
        'src/string.cpp',
        'src/strstream.cpp',
        'src/system_error.cpp',
        'src/thread.cpp',
        'src/typeinfo.cpp',
        'src/utility.cpp',
        'src/valarray.cpp',
      ],
      'actions': [
        {
          'action_name': 'copy_abi_headers',
          'inputs': [
            'copy_abi_headers.py',
          ],
          'outputs': [
            '<@(abi_headers)',
          ],
          'action': ['python', 'copy_abi_headers.py', '<(INTERMEDIATE_DIR)'],
          'message': 'Copying ABI headers to <(INTERMEDIATE_DIR)',
        },
      ],
    },

    {
      'target_name': 'c++',
      'type': 'shared_library',
      'dependencies': [
        '../libcxxabi/libcxxabi.gyp:c++abi',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          'include',
        ],
      },
      'defines': [
        '_LIBCPP_NO_EXCEPTIONS',
        'cxx_EXPORTS',
      ],
      'cflags': [
        '-O3',
        '-std=c++11',
        '-nostdinc++',
        '-fPIC',
        '-fno-exceptions',
        '-pedantic',
        '-Wall',
        '-W',
        '-Wno-unused-parameter',
        '-Wwrite-strings',
        '-Wno-long-long',
        '-Wno-error',
      ],
      'cflags!': [
        '-O0',  # libc++.so loses |~basic_string()| with this flag.
      ],
      'ldflags': [
        '-nodefaultlibs',
        '-lpthread',
        '-lc',
        '-lm',
        '-lrt',
        '-lgcc_s',
      ],
      'include_dirs': [
        'include',
      ],
      'sources': [
        'src/algorithm.cpp',
        'src/bind.cpp',
        'src/chrono.cpp',
        'src/condition_variable.cpp',
        'src/debug.cpp',
        'src/exception.cpp',
        'src/future.cpp',
        'src/hash.cpp',
        'src/ios.cpp',
        'src/iostream.cpp',
        'src/locale.cpp',
        'src/memory.cpp',
        'src/mutex.cpp',
        'src/new.cpp',
        'src/optional.cpp',
        'src/random.cpp',
        'src/regex.cpp',
        'src/shared_mutex.cpp',
        'src/stdexcept.cpp',
        'src/string.cpp',
        'src/strstream.cpp',
        'src/system_error.cpp',
        'src/thread.cpp',
        'src/typeinfo.cpp',
        'src/utility.cpp',
        'src/valarray.cpp',
      ],
    },
  ],
}
