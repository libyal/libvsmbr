#!/usr/bin/env python
#
# Python-bindings partition type test script
#
# Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyvsmbr


class PartitionTypeTests(unittest.TestCase):
  """Tests the partition type."""

  def test_read_buffer(self):
    """Tests the read_buffer function."""
    if not unittest.source:
      return

    vsmbr_partition = pyvsmbr.partition()

    vsmbr_partition.open(unittest.source)

    file_size = vsmbr_partition.get_size()

    # Test normal read.
    data = vsmbr_partition.read_buffer(size=4096)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    if file_size < 4096:
      data = vsmbr_partition.read_buffer()

      self.assertIsNotNone(data)
      self.assertEqual(len(data), file_size)

    # Test read beyond file size.
    if file_size > 16:
      vsmbr_partition.seek_offset(-16, os.SEEK_END)

      data = vsmbr_partition.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 16)

    with self.assertRaises(ValueError):
      vsmbr_partition.read_buffer(size=-1)

    vsmbr_partition.close()

    # Test the read without open.
    with self.assertRaises(IOError):
      vsmbr_partition.read_buffer(size=4096)

  def test_read_buffer_file_object(self):
    """Tests the read_buffer function on a file-like object."""
    if not unittest.source:
      return

    file_object = open(unittest.source, "rb")

    vsmbr_partition = pyvsmbr.partition()

    vsmbr_partition.open_file_object(file_object)

    file_size = vsmbr_partition.get_size()

    # Test normal read.
    data = vsmbr_partition.read_buffer(size=4096)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    vsmbr_partition.close()

  def test_read_buffer_at_offset(self):
    """Tests the read_buffer_at_offset function."""
    if not unittest.source:
      return

    vsmbr_partition = pyvsmbr.partition()

    vsmbr_partition.open(unittest.source)

    file_size = vsmbr_partition.get_size()

    # Test normal read.
    data = vsmbr_partition.read_buffer_at_offset(4096, 0)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    # Test read beyond file size.
    if file_size > 16:
      data = vsmbr_partition.read_buffer_at_offset(4096, file_size - 16)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 16)

    with self.assertRaises(ValueError):
      vsmbr_partition.read_buffer_at_offset(-1, 0)

    with self.assertRaises(ValueError):
      vsmbr_partition.read_buffer_at_offset(4096, -1)

    vsmbr_partition.close()

    # Test the read without open.
    with self.assertRaises(IOError):
      vsmbr_partition.read_buffer_at_offset(4096, 0)

  def test_seek_offset(self):
    """Tests the seek_offset function."""
    if not unittest.source:
      return

    vsmbr_partition = pyvsmbr.partition()

    vsmbr_partition.open(unittest.source)

    file_size = vsmbr_partition.get_size()

    vsmbr_partition.seek_offset(16, os.SEEK_SET)

    offset = vsmbr_partition.get_offset()
    self.assertEqual(offset, 16)

    vsmbr_partition.seek_offset(16, os.SEEK_CUR)

    offset = vsmbr_partition.get_offset()
    self.assertEqual(offset, 32)

    vsmbr_partition.seek_offset(-16, os.SEEK_CUR)

    offset = vsmbr_partition.get_offset()
    self.assertEqual(offset, 16)

    vsmbr_partition.seek_offset(-16, os.SEEK_END)

    offset = vsmbr_partition.get_offset()
    self.assertEqual(offset, file_size - 16)

    vsmbr_partition.seek_offset(16, os.SEEK_END)

    offset = vsmbr_partition.get_offset()
    self.assertEqual(offset, file_size + 16)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vsmbr_partition.seek_offset(-1, os.SEEK_SET)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vsmbr_partition.seek_offset(-32 - file_size, os.SEEK_CUR)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vsmbr_partition.seek_offset(-32 - file_size, os.SEEK_END)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vsmbr_partition.seek_offset(0, -1)

    vsmbr_partition.close()

    # Test the seek without open.
    with self.assertRaises(IOError):
      vsmbr_partition.seek_offset(16, os.SEEK_SET)


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()


  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])



  unittest.main(argv=unknown_options, verbosity=2)
