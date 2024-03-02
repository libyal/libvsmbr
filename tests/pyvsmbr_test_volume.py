#!/usr/bin/env python
#
# Python-bindings volume type test script
#
# Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyvsmbr


class VolumeTypeTests(unittest.TestCase):
  """Tests the volume type."""

  def test_signal_abort(self):
    """Tests the signal_abort function."""
    vsmbr_volume = pyvsmbr.volume()

    vsmbr_volume.signal_abort()

  def test_open(self):
    """Tests the open function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsmbr_volume = pyvsmbr.volume()

    vsmbr_volume.open(test_source)

    with self.assertRaises(IOError):
      vsmbr_volume.open(test_source)

    vsmbr_volume.close()

    with self.assertRaises(TypeError):
      vsmbr_volume.open(None)

    with self.assertRaises(ValueError):
      vsmbr_volume.open(test_source, mode="w")

  def test_open_file_object(self):
    """Tests the open_file_object function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    if not os.path.isfile(test_source):
      raise unittest.SkipTest("source not a regular file")

    vsmbr_volume = pyvsmbr.volume()

    with open(test_source, "rb") as file_object:

      vsmbr_volume.open_file_object(file_object)

      with self.assertRaises(IOError):
        vsmbr_volume.open_file_object(file_object)

      vsmbr_volume.close()

      with self.assertRaises(TypeError):
        vsmbr_volume.open_file_object(None)

      with self.assertRaises(ValueError):
        vsmbr_volume.open_file_object(file_object, mode="w")

  def test_close(self):
    """Tests the close function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsmbr_volume = pyvsmbr.volume()

    with self.assertRaises(IOError):
      vsmbr_volume.close()

  def test_open_close(self):
    """Tests the open and close functions."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      return

    vsmbr_volume = pyvsmbr.volume()

    # Test open and close.
    vsmbr_volume.open(test_source)
    vsmbr_volume.close()

    # Test open and close a second time to validate clean up on close.
    vsmbr_volume.open(test_source)
    vsmbr_volume.close()

    if os.path.isfile(test_source):
      with open(test_source, "rb") as file_object:

        # Test open_file_object and close.
        vsmbr_volume.open_file_object(file_object)
        vsmbr_volume.close()

        # Test open_file_object and close a second time to validate clean up on close.
        vsmbr_volume.open_file_object(file_object)
        vsmbr_volume.close()

        # Test open_file_object and close and dereferencing file_object.
        vsmbr_volume.open_file_object(file_object)
        del file_object
        vsmbr_volume.close()

  def test_get_bytes_per_sector(self):
    """Tests the get_bytes_per_sector function and bytes_per_sector property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsmbr_volume = pyvsmbr.volume()

    vsmbr_volume.open(test_source)

    try:
      bytes_per_sector = vsmbr_volume.get_bytes_per_sector()
      self.assertIsNotNone(bytes_per_sector)

      self.assertIsNotNone(vsmbr_volume.bytes_per_sector)

    finally:
      vsmbr_volume.close()

  def test_get_number_of_partitions(self):
    """Tests the get_number_of_partitions function and number_of_partitions property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsmbr_volume = pyvsmbr.volume()

    vsmbr_volume.open(test_source)

    try:
      number_of_partitions = vsmbr_volume.get_number_of_partitions()
      self.assertIsNotNone(number_of_partitions)

      self.assertIsNotNone(vsmbr_volume.number_of_partitions)

    finally:
      vsmbr_volume.close()

  def test_get_partition(self):
    """Tests the get_partition function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsmbr_volume = pyvsmbr.volume()

    vsmbr_volume.open(test_source)

    try:
      if not vsmbr_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      partition = vsmbr_volume.get_partition(0)
      self.assertIsNotNone(partition)

    finally:
      vsmbr_volume.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
