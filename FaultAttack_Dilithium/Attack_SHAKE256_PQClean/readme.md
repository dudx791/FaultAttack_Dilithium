The `pqclean_L2` folder within the `firmware` directory contains the firmware C programs running on the STM32F405, as well as the assembly files (.lss) compiled using `arm-none-eabi-gcc` and the hexadecimal files (.hex) uploaded with Chipwhisperer.

In the `pqclean_L2` folder, the main function is located in `PQCgenKAT_sign.c`.

If you need to run our attack code, ensure that you have the Chipwhisperer software installed, and place the `pqclean_L2` folder in the `chipwhisperer\hardware\victims\firmware` path.

The `attack_code` folder contains four `.ipynb` files for testing the success rate of fault attacks, each with output results. The four files correspond to the four locations where we proposed attacks on the SHAKE256 function implemented in PQCclean in our paper.

As we noted in the paper, we need to perform fault injection attacks on two different messages so that they output the same ρ′. In each `.ipynb` file, we conduct 1000 fault injection attacks, outputting the seed ρ′ after each attack and storing it in the list `rho_list`. Finally, we calculate the success rate of the fault injection attacks based on the maximum number of identical ρ′ values in `rho_list`.

For example, the attack code in `test_suc_ixy1.ipynb` corresponds to the first attack position on SHAKE256 proposed in our paper. After conducting 1000 fault injection attacks, we found that there were 773 identical ρ′ values in `rho_list`. Therefore, we calculated the success rate of the fault injection attack to be 77.3% by dividing 773 by 1000.