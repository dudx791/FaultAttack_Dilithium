The `pqm4_L2_extract folder within the `firmware` directory contains the firmware C programs running on the STM32F405, as well as the assembly files (.lss) compiled using `arm-none-eabi-gcc` and the hexadecimal files (.hex) uploaded with Chipwhisperer.

In the `pqm4_L2_extract folder, the main function is located in `PQCgenKAT_sign.c`. In the `PQCgenKAT_sign.c` file, we define the `enc_password` function, which calls the `test_fun2` function located in the `sign.c` file.

The `test_fun2` function calls the `stream256_squeezeblocks` function, and we have conducted a separate attack on the `stream256_squeezeblocks` function. Using the code `for(int kk=0; kk < 136; kk++) p[kk] = buf[kk];`, we output the data from the `buf` array.

If you need to run our attack code, ensure that you have the Chipwhisperer software installed, and place the `pqm4_L2_extract folder in the `chipwhisperer\hardware\victims\firmware` path.

The `attack_code` folder contains two `.ipynb` files for testing the success rate of fault attacks. One file (`extract_suc_test.ipynb`) shows the fault injection success rate obtained after our first attack, while the other file (`re_attack_suc.ipynb`) presents the success rate from our second fault injection attack test. The success rate in `re_attack_suc.ipynb` shows a significant improvement compared to the first attack.

In the `.ipynb` file, we define a list called `no_fault_list` and initialize it as an empty list. After defining this empty list, we execute the firmware program on the STM32F405 without any faults and output the `buf` array. We then store the 136 data points from the output `buf` into the `no_fault_list`.

Next, we define the function `panduan_other(i, list1, list2)`, which checks whether all elements in `list1` and `list2` are the same, except for the i+1-th element.

After setting the fault parameters, we run the process 1000 times, injecting a fault during each run. After each attack, we output the `buf` array. If all elements in the `buf` array, except for the first element, are the same, we consider that our attack successfully changed the first element of the `buf` array to 0.

Finally, we calculate the success rate of the fault attacks by dividing the number of successful attacks by 1000.

