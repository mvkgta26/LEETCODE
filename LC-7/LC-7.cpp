int reverse(int x) 
{
	int num = x;
	int reversed = 0;
	
	
	while ( num != 0 )
	{
		reversed = reversed*10 + (num % 10);
		num = num/10;
	}

	return reversed;
	
	
		// // Obtain absolute value of the x. Use unsigned int because magnitude of negative value could exceed signed int limit
	// unsigned int positive_x = abs(x);

	// unsigned int abs_reversed = reverse_unsigned_num(positive_x);

	// // Overflow cases
	// unsigned int positive_max_val = INT32_MAX;    // 2^31 - 1 
	// unsigned int neg_max_abs_val = positive_max_val + 1;   // 2^31 is max negative value

	// if ( x >= 0 && abs_reversed > positive_max_val )
	// {
	// 	return 0;
	// }

	// else if ( x < 0 && abs_reversed > neg_max_abs_val )
	// {
	// 	return 0;
	// }


	// int output;
	
	// if (x < 0)
	// 	output = abs_reversed * (-1);

	// else
	// 	output = abs_reversed;

	// return output;
}