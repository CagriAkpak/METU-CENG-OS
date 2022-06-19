# METU CENG 
## Operating Systems Spring 2022 Homework 1

- Homework text and parser files have been added to the folder.

- Shell application for solution is added.

- Parser updated to fix a small memory leak issue and return warning.

### Grade Distribution

How testcases are divided is given in this part.

- 20 Points: Bundles with no file redirection or pipeline. 
- 20 Points: Bundles with either input or output redirection.
- 10 Points: Bundles with both input and output file redirections.
- 20 Points: Pipeline with bundles containing only a single process.
- 30 Points: Pipeline with bundles containing multiple processes.

Although there is small chance these values may change. The changes will be small.

### How to Use Grader

You need to put your compiled ./hw1 executable and provided ./bshell program to the same folder. Then you can run grader directly.

Run: 

./grader

It will create its testcases and necessary scripts. Testcases and one input redirection file will remain so that you can test your codes. The rest will be deleted at the end.

It will give you the difference in inputs between solution and your code. They will be sorted and therefore a little hard to understand. For this reason you can run the inputs directly to see where you went wrong.

Before running your codes, you need to create outputs folder. You can run them with following format:

mkdir outputs

./hw1 < inputs/inputX.txt


were X is the number of the testcase you want to run. There are 50 testcases each and they all are 2 points. If there are redirections in the testcase, the outputs will be create in the outputs directory. Their names will be in this format tXoN.txt where X is similarly the testcase number and N is the which pipeline produced that output. Of course if there are no redirections, it will be printed to stdout as per your code.

I will be accepting corrections as long as they are moderately small. This is especially true for people who received 0. The size of the patch files should not exceed 2 kbs.
Your late submission penalties are already applied to them.

#### Creating patch files
You can use the following command to create your patch files. Just replace the file names with your sources.

diff -u OriginalFile UpdatedFile > PatchFile


