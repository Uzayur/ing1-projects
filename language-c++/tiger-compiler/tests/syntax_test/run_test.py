from subprocess import PIPE, run
import os
import subprocess
import unittest

class Testtest(unittest.TestCase):
    def test(self):
        exit1 = subprocess.run("../../src/tc -X --parse cross_functions.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -X --parse methods_dec.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse multiple_args_function.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_array_dec.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_array_for.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_array.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_attribut.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -X --parse simple_class.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_for.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_function.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_hello.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_prints.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse simple_string.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -o -X --parse simple_type.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse triple_print.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse while_functions.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

        exit1 = subprocess.run("../../src/tc -X --parse backslash_in_comment.tig; echo $?", stdout=PIPE, shell=True)
        exit2 = subprocess.run("echo 0", stdout=PIPE, shell=True)
        self.assertEqual(exit1.stdout, exit2.stdout)

if __name__ == '__main__':
    unittest.main()
