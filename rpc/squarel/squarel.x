struct squarel_in
{
	long in;
};

struct squarel_out
{
	long out;
};

program SQUAREL_PROG
{
	version SQUAREL_VERS1
	{
		squarel_out SQUARELPROG(squarel_in) = 1;	/* procedure number */
	} = 1;		/* version number */

	version SQUAREL_VERS2
	{
		squarel_out SQUARELPROG(squarel_in) = 1;
	} = 2;		/* version number */
} = 0x31230000;	/* program number */
