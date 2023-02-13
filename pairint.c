#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pairint {
	unsigned int pos;
	unsigned int neg;
} pairint;

pairint
pairint_new(int x)
{
	assert(x != INT_MIN);

	pairint inited = (pairint){
		.pos=0,
		.neg=0
	};

	if (x > 0) {
		inited.pos = x;
	}

	if (x < 0) {
		inited.neg = abs(x);
	}

	return inited;
}

pairint
pairint_norm(pairint x)
{
	pairint normed = (pairint){
		.pos=0,
		.neg=0
	};

	if (x.pos > x.neg) {
		normed.pos = x.pos - x.neg;
	}

	if (x.pos < x.neg) {
		normed.neg = x.neg - x.pos;
	}

	return normed;
}

int
pairint_sign(pairint x)
{
	return (x.pos > x.neg) - (x.pos < x.neg);
}

pairint
pairint_neg(pairint x)
{
	return (pairint){
		.pos=x.neg,
		.neg=x.pos
	};
}

pairint
pairint_add(pairint x, pairint y)
{
	pairint sum = (pairint){
		.pos=x.pos + y.pos,
		.neg=x.neg + y.neg
	};
	return pairint_norm(sum);
}

pairint
pairint_sub(pairint x, pairint y)
{
	return pairint_add(x, pairint_neg(y));
}

pairint
pairint_mul(pairint x, pairint y)
{
	pairint prod = (pairint){
		.pos=x.pos * y.pos + x.neg * y.neg,
		.neg=x.pos * y.neg + x.neg * y.pos
	};
	return pairint_norm(prod);
}

void
pairint_print(pairint x)
{
	if (x.pos > x.neg) {
		printf("%d\n", x.pos - x.neg);
	} else if (x.pos < x.neg) {
		printf("-%d\n", x.neg - x.pos);
	} else {
		printf("0\n");
	}
}

int
main(void)
{
	{
		pairint x = pairint_new(3);
		pairint y = pairint_new(2);
		pairint_print(pairint_add(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(-1);
		pairint_print(pairint_add(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(2);
		pairint_print(pairint_add(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(1);
		pairint_print(pairint_add(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(0);
		pairint_print(pairint_add(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(3);
		pairint_print(pairint_mul(x, y));
	}
	{
		pairint x = pairint_new(2);
		pairint y = pairint_new(3);
		pairint_print(pairint_mul(x, y));
	}
	{
		pairint x = pairint_new(-2);
		pairint y = pairint_new(-3);
		pairint_print(pairint_mul(x, y));
	}
	{
		pairint x = pairint_new(2);
		pairint y = pairint_new(3);
		pairint_print(pairint_sub(x, y));
	}

	return 0;
}
