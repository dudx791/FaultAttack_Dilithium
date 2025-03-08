The `pqm4_L2` folder within the `firmware` directory contains the firmware C programs running on the STM32F405, as well as the assembly files (.lss) compiled using `arm-none-eabi-gcc` and the hexadecimal files (.hex) uploaded with Chipwhisperer.

In the `pqm4_L2` folder, the main function is located in `PQCgenKAT_sign.c`.

If you need to run our attack code, ensure that you have the Chipwhisperer software installed, and place the `pqm4_L2` folder in the `chipwhisperer\hardware\victims\firmware` path.

The `attack_code` folder contains one `.ipynb` file for testing the success rate of fault attacks, in which we conduct success rate tests on the 32 attack positions proposed for SHAKE256 in the paper.

As we indicated in the paper, we need to perform fault injection attacks on two different messages so that they output the same ρ′. We preemptively obtained the ρ′ values for different attack positions through simulation experiments and stored the first five characters of the 32 ρ′ values that could be obtained through attacks in `small_list1` to `small_list32`. For each attack position, we conduct 1000 fault injection attacks, outputting the seed ρ′ after each attack and comparing it with the corresponding `small_list`. If the ρ′ obtained after the current attack matches the `small_list`, we consider the fault injection attack successful. We calculate the success rate of the fault injection attacks by dividing the number of matching ρ′ values by 1000.

By observing the output results of the attacks at each position, we found that when the attack is successful, all output ρ′ values are the same. This aligns with the desired attack outcome proposed in our paper, where attacking two different messages generates the same ρ′.