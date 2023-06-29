from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../src/tc -X --parse bad_array.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -X --parse bad_class.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_for.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_functions_dec.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -X --parse bad_method.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_string.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_token.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_type_dec.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse bad_while.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse basic_lexical.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse type_nil.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 3", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse unvalid_file.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 1", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse too_large_int.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse unterminated_comment.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse unterminated_string.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 2", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
