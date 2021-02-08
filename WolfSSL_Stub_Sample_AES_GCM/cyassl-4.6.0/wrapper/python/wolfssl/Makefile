# Makefile
#
# Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfSSL.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#/
#/

.PHONY : all clean clean-test clean-build clean-pyc install test check upload

# builds the module
all :
	python ./setup.py build

#builds and installs the module
install : all
	python ./setup.py install

## removes all build, test, coverage and Python artifacts
clean : clean-test clean-build clean-pyc

## removes test and coverage artifacts
clean-test :
	rm -rf .coverage .tox/ htmlcov/

## removes build artifacts
clean-build :
	rm -rf build/ dist/ .eggs/
	find . -name '*.egg-info' -exec rm -rf {} +
	find . -name '*.egg' -exec rm -v {} +

## removes Python file artifacts
clean-pyc :
	find src test -name '__pycache__' -exec rm -rf {} +
	find src test -name '*.pyc' -exec rm -f {} +
	find src test -name '*.pyo' -exec rm -f {} +

# runs unit tests
check : test

test : clean-pyc
	tox

# publishes module at pypi
upload : test
	python ./setup.py sdist upload
