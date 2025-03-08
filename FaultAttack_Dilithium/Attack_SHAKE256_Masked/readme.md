The `maskdilithium_fualtAttack` folder within the `firmware` directory contains the firmware C programs running on the STM32F405, as well as the assembly files (.lss) compiled using `arm-none-eabi-gcc` and the hexadecimal files (.hex) uploaded with Chipwhisperer.

In the `maskdilithium_fualtAttack` folder, the main function is located in `mask_main.c`. In the `mask_main.c` file, we define the `mask_hash` function, which is used to perform fault injection attacks on the masked SHAKE256 function.

In the `mask_hash` function, we use the code `for(int ii=0; ii < 180; ii++) p[ii] = seed_y[ii];` to output the attacked ρ′.

If you need to run our attack code, ensure that you have the Chipwhisperer software installed, and place the `maskdilithium_fualtAttack` folder in the `chipwhisperer\hardware\victims\firmware` path.

The `attack_code` folder contains four `.ipynb` files for testing the success rate of fault attacks, each with output results. The four files correspond to the four attack positions on the masked SHAKE256 function proposed in our paper.

Since we are attacking the masked implementation of the SHAKE256 function, the knowledge of parameters `masked_K` and `tr` during the signing process does not affect our attack. Therefore, in each `.ipynb` file, we define the functions `get_maskedkey()` and `get_tr()` to read the `masked_K` and `tr` stored in the `data.bin` and `tr.bin` files. Finally, we use randomly generated messages MMM, `masked_K`, and `tr` as input data for the STM32F405 to run the masked SHAKE256 function, outputting ρ′ after each attack.

We first obtained the successful ρ′ values from a simulation experiment and stored them in `smalllist`. Then, we conducted fault injection attacks on 1000 randomly generated messages, comparing the output ρ′ after the attacks with the successful ρ′ obtained from the simulation. If they match, we consider the attack successful. The success rate of our fault injection attacks is calculated by dividing the number of successful attacks by 1000.

From the output results, we found that the ρ′ values after each successful attack were the same, which aligns with our expectation in the paper that two different messages would output the same ρ′ after the attack.