/***************************************************************************************************************/
/**                                                 BIN.H                                                     **/
/***************************************************************************************************************/

#ifndef BIN_H
#define BIN_H

#define TRUE 1
#define FALSE 0

typedef t_uint64 t_uint64;
typedef unsigned short t_bit;
typedef unsigned short t_binw;
typedef unsigned short t_hex;
typedef char t_hexw;
unsigned short BINW_SZ;
unsigned short HEXW_SZ;
unsigned short binw_set_sz();

void bin_example();

void     binw_destroy(t_binw *p);
t_binw  *binw_create();
t_binw  *binw_create_dyn(t_uint64 x);
t_binw  *binw_create_random();
void     binw_display(t_binw *p, const char *title);

t_bit bit_not (t_bit b         );
t_bit bit_or  (t_bit a, t_bit b);
t_bit bit_nor (t_bit a, t_bit b);
t_bit bit_and (t_bit a, t_bit b);
t_bit bit_nand(t_bit a, t_bit b);
t_bit bit_xor (t_bit a, t_bit b);
t_bit bit_xnor(t_bit a, t_bit b);

void    binw_not_void(t_binw *b_in);
t_binw *binw_not     (t_binw *b);
t_binw *binw_or      (t_binw *a, t_binw *b);
t_binw *binw_nor     (t_binw *a, t_binw *b);
t_binw *binw_and     (t_binw *a, t_binw *b);
t_binw *binw_nand    (t_binw *a, t_binw *b);
t_binw *binw_xor     (t_binw *a, t_binw *b);
t_binw *binw_xnor    (t_binw *a, t_binw *b);

t_bit    binw_zero_compare      (t_binw *b_in);
t_binw  *binw_fill_zero         (t_binw *b, t_uint64 offset );
t_binw  *binw_fill_one          (t_binw *b, t_uint64 offset );
t_bit    binw_check_sign        (t_binw *a);

t_binw  *binw_1_complement      (t_binw *b);
void     binw_1_complement_void (t_binw *b);
t_binw  *binw_get_absolute_value(t_binw *b);
t_binw **binw_get_matrix        (t_binw *a, t_binw *b, t_uint64 *binw_array_sz);
t_bit    binw_cmp               (t_binw *a, t_binw *b);
t_bit    binw_get_effective_sz  (t_binw *p);
t_uint64 binw_cmp_effective_sz  (t_binw *a, t_binw *b);

t_bit           binw_multiply_get_sign( t_binw *a, t_binw *b );
t_uint64  binw_multiply_get_new_sz(t_binw *a, t_binw *b);
t_uint64  binw_multiply_check_carry_overflow(t_binw *a, t_binw *b);
t_binw         *binw_multiply(t_binw *a, t_binw *b);

t_binw  *bit_add(t_bit a, t_bit b, t_bit r);
t_bit    binw_add_get_sign(t_binw *a, t_binw *b);
t_binw  *binw_add(t_binw *a, t_binw *b);
t_binw  *binw_add_limit(t_binw *a, t_binw *b);
void binw_add_recursive(t_binw **matrix, unsigned short matrix_sz, unsigned short index_sz, t_binw **partial_sum);

t_binw  *dec_to_binw( long long int x );
long long int binw_to_dec(t_binw *b);
t_binw *str_to_binw(const char *str, t_uint64 *binw_sz, t_uint64 sz);
char *binw_to_str(t_binw *b_in, t_uint64 b_sz, t_uint64 *str_sz, t_uint64 binw_sz);

# endif
