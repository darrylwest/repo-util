#!/usr/bin/env bash
# dpw@Darryls-iMac.localdomain
# 2022-01-28 01:41:38
#


set -eu

function clean() {
  printf "clean all from build folder...\n"
  /bin/rm -fr build
}

function config() {
  (
    [ -f build/Makefile ] || {
      printf "create build folder...\n"
      /bin/rm -fr build
      mkdir build && cd build && cmake ../
    }
  )
}

function build() {
  ( cd build && make )
}

function run() {
  (
    printf "run the examples...\n"
    cd build 
    ./repos --version
    ./repos --help
  )
}

function watch() {
  printf "watching from pid: $$\n"
  watchexec -c -d 250 -e .cpp,.hpp,.txt -p -i build -w ./ ./mk
}

function run_tests() {
  ./build/test/repo_unit_tests --durations yes
}


echo "program: $0"
case $0 in
  *watch)
    watch
    ;;
  *build)
    build
    ;;
  *clean)
    clean
    ;;
  *clean-mk)
    time ( clean && config && build && run && run_tests )
    ;;
  *)
    config && build && run && run_tests
    ;;
esac

[ $? ] && printf "Ok\n" || printf "Failed...\n"

exit 0

