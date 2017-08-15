import os
import os.path
import shutil

rootdir = ".\\"

# all_the_text_of_Makefile_config = open(
#     "..\\1_splash2-master\\Makefile.config").read()

malicious_code_4_c = "..\\2_bullmoose\\BullMoose_4_pthread_NoOutPut.c"
malicious_code_4_h = "..\\2_bullmoose\\BullMoose_4_pthread_NoOutPut.h"

for parent, dirnames, filenames in os.walk(rootdir):
    for dirname in dirnames:
        if dirname == "programme":

            if os.path.exists(os.path.join(parent, dirname, "BullMoose_4_pthread_NoOutPut.c")):
                os.remove(os.path.join(parent, dirname,
                                       "BullMoose_4_pthread_NoOutPut.c"))
                os.remove(os.path.join(parent, dirname,
                                       "BullMoose_4_pthread_NoOutPut.h"))

            shutil.copy(malicious_code_4_c, os.path.join(
                parent, dirname, "bullmoose.c"))
            shutil.copy(malicious_code_4_h, os.path.join(
                parent, dirname, "bullmoose.h"))

    #         for filename in filenames:
    #             shutil.move(os.path.join(parent, filename),
    #                         os.path.join(parent, dirname))

    # for filename in filenames:

        # if "makefile" == filename:

            # # replace makefile
            # infile = open(os.path.join(parent, filename), "r")
            # outfile = open(os.path.join(parent, "temp_makefile"), "w")
            # lines = infile.readlines()
            # for line in lines:

            #     # outfile.write(line.replace(
            #     #     "include ..\\..\\Makefile.config", all_the_text_of_Makefile_config))

            #     if line.startswith("TARGET"):
            #         outfile.write("TARGET = programme\\n")
            #     elif line.startswith("include"):
            #         outfile.write(
            #             "include ..\\..\\..\\null_macros\\Makefile.config\\n")
            #     else:
            #         outfile.write(line)
            # infile.close()
            # outfile.close()
            # os.remove(os.path.join(parent, filename))
            # shutil.move(os.path.join(parent, "temp_makefile"),
            #             os.path.join(parent, filename))

            # replace malicious code
            # infile = open(os.path.join(parent, filename), "r")
            # outfile = open(os.path.join(parent, "temp_makefile"), "w")
            # lines = infile.readlines()
            # for line in lines:
            #         outfile.write(line.replace(
            #             "OBJS =", "OBJS = bullmoose.o"))
            # outfile.write("bullmoose.c: bullmoose.h")
            # infile.close()
            # outfile.close()
            # os.remove(os.path.join(parent, filename))
            # shutil.move(os.path.join(parent, "temp_makefile"),
            #             os.path.join(parent, filename))

appdir = ".\\apps"
detectdir = ".\\apps.LCLB.detect.new"
squences = ['4132', '4231', '4321']
for file in os.listdir(appdir):
    app_name = os.path.join(appdir, file)
    print(app_name)
    path_name = os.path.join(detectdir, file)
    print(path_name)
    if not os.path.exists(path_name):
        os.makedirs(path_name)
    for squence in squences:
        squence_name = os.path.join(path_name, squence)
        print(squence_name)
        if not os.path.exists(squence_name):
            os.makedirs(squence_name)
        for order in '123456':
            order_name = os.path.join(squence_name, order)
            print(order_name)
            if os.path.exists(order_name):
                os.removedirs(order_name)
            shutil.copytree (app_name, order_name)