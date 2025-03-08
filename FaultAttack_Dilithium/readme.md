The four folders above contain the source code for conducting fault attacks on the SHAKE256 implementations from PQClean, the SHAKE256 implementation from pqm4, the masked SHAKE256 function, and the random number generation function y.

Each folder includes the firmware code uploaded to the STM32F405 (in the `firmware` folder), the attack code running on the PC interface provided by Chipwhisperer (in the `attack_code` folder), and more detailed information (in the `readme` file).

The `firmware` folder contains source code that can be compiled using `arm-none-eabi-gcc`, along with a Makefile. It also includes the hexadecimal program (.hex) that can be directly uploaded to Chipwhisperer after compilation.

In the `attack_code` folder, there is one or more `.ipynb` files showcasing the Python code used for our attacks.

In each folder, the `readme` provides a detailed explanation of what the `.ipynb` files in the `attack_code` do.

If the .ipynb files in the attack_code folder are too large to be displayed on GitHub's web interface, please download them and open them using VSCode or Jupyter Notebook.
