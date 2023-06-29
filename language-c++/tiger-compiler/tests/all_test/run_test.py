from subprocess import PIPE, run
import os
import subprocess
import unittest

class Test(unittest.TestCase):

    def test_syntax(self):
        exit1 = subprocess.run("cd ../syntax_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_syntax_error(self):
        exit1 = subprocess.run("cd ../syntax_error_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_pretty_printer(self):
        exit1 = subprocess.run("cd ../pretty_printer_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_import(self):
        exit1 = subprocess.run("cd ../import_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_binder(self):
        exit1 = subprocess.run("cd ../binder_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_escape(self):
        exit1 = subprocess.run("cd ../escape_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_renamer(self):
        exit1 = subprocess.run("cd ../renamer_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_type(self):
        exit1 = subprocess.run("cd ../type_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

    def test_given(self):
        exit1 = subprocess.run("cd ../given_test; python3 run_test.py; echo $?; cd ../all_test", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
