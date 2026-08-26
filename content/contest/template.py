'''
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Minimal fast I/O scaffold for Python solutions. finput reads
 * a line at a time from a buffered copy of stdin; fprint writes to stdout.
 * Time: O(1) setup.
 * Status: untested
'''
import os, sys, io
finput = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
fprint = sys.stdout.write
