#!/bin/bash
wget -O example_file https://www.media.volvocars.com/global/en-gb/corporate/this-is-volvo
sed -i "s/Volvo/The best company ever/g" example_file