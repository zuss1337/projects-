#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *ptr_str = str;

  va_list args;
  va_start(args, format);

  int count_prnt_sym = 0;
  while (*format) {
    if (*format == '%') {
      *ptr_str = '\0';
      format++;
      const char *static_format = format;
      struct flags status_flags = {false};
      format += flags_processing(format, &status_flags);
      int width = 0;
      format += width_processing(format, &width, args);
      int precision = -1;
      format += precision_processing(format, &precision, args);
      if (precision != -1) {
        status_flags.nul = false;
      }

      int shift = 0;
      char *specif_str = specifier_processing(format, args, &shift,
                                              &status_flags, &precision, str);
      format += shift;
      if (specif_str != s21_NULL && precision != -2 && width != -1) {
        specif_str =
            out_str_formatting(specif_str, status_flags, width, precision);

        int len = s21_strlen(specif_str);
        s21_strncat(ptr_str, specif_str, len);
        ptr_str += len;

        free(specif_str);
        specif_str = s21_NULL;
      } else {
        *ptr_str = '%';
        ptr_str++;
        *ptr_str = '\0';
        format = static_format;
        count_prnt_sym++;
      }
    } else {
      *ptr_str = *format;
      ptr_str++;
      *ptr_str = '\0';
      format++;
      count_prnt_sym++;
    }
  }
  *ptr_str = '\0';
  va_end(args);
  return s21_strlen(str);
}

int precision_processing(const char *format, int *precision, va_list args) {
  int shift = 0;
  if (*format == '.') {
    shift++;
    format++;
    if (*format == '*') {
      shift++;
      *precision = va_arg(args, int);
    } else {
      *precision = 0;
      while (true) {
        if ((*format > 47 && *format < 58)) {
          *precision = 10 * (*precision) + (int)(*format) - 48;
          format++;
          shift++;
        } else {
          break;
        }
      }
    }
    if (*precision < 0) {
      *precision = -2;
    }
  }

  return shift;
}

int width_processing(const char *format, int *width, va_list args) {
  int shift = 0;

  if (*format == '*') {
    shift++;
    *width = va_arg(args, int);
  } else {
    while (true) {
      if ((*format > 47 && *format < 58)) {
        *width = 10 * (*width) + (int)(*format) - 48;
        format++;
        shift++;
      } else {
        break;
      }
    }
    if (*width < 0) {
      *width = -1;
    }
  }
  return shift;
}

int flags_processing(const char *format, struct flags *status_flags) {
  int shift = 0;
  int stop = 0;

  while (!stop) {
    switch (*format) {
      case '-':
        shift++;
        status_flags->hyphen = true;
        break;

      case '+':
        shift++;
        status_flags->plus = true;
        break;

      case ' ':
        shift++;
        status_flags->space = true;
        break;

      case '#':
        shift++;
        status_flags->sharp = true;
        break;

      case '0':
        shift++;
        status_flags->nul = true;
        break;

      default:
        stop = 1;
        format--;
        break;
    }
    format++;
  }

  if (status_flags->plus) {
    status_flags->space = false;
  }
  if (status_flags->hyphen) {
    status_flags->nul = false;
  }

  return shift;
}

char *specifier_processing(const char *format, va_list args, int *shift,
                           struct flags *status_flags, int *precision,
                           char *end_str) {
  bool l_flag = false;
  bool L_flag = false;

  switch (*format) {
    case 'h':
      // h_flag = true;
      break;

    case 'l':
      l_flag = true;
      break;

    case 'L':
      L_flag = true;
      break;

    default:
      (*shift)--;
      format--;
      break;
  }
  format++;
  (*shift)++;
  //==================================
  char *out_str = s21_NULL;
  switch (*format) {
    case 'c':
      out_str = malloc(2);
      if (l_flag) {
        out_str[0] = va_arg(args, unsigned int);
      } else
        out_str[0] = va_arg(args, int);

      out_str[1] = '\0';
      status_flags->plus = false;
      status_flags->space = false;
      status_flags->nul = false;
      *precision = -1;
      break;

    case 'd':
    case 'i':
      status_flags->spec_int = true;
      if (l_flag) {
        out_str = from_int_to_string(va_arg(args, long int));
      } else
        out_str = from_int_to_string(va_arg(args, int));
      break;

    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      status_flags->spec_float = true;
      long double src;

      if (*precision == -1) *precision = 6;

      if (L_flag) {
        src = va_arg(args, long double);
      } else {
        src = va_arg(args, double);
      }

      if (*format == 'e' || *format == 'E') {
        out_str = mant_exp_str(src, *precision, status_flags->sharp, *format);
      } else if (*format == 'f') {
        out_str = from_double_to_str(src, *precision, status_flags->sharp);
      } else if (*format == 'g' || *format == 'G') {
        out_str =
            short_note_gG(src, *precision, status_flags->sharp, (*format) - 2);
      }

      break;

    case 'o':
    case 'u':
    case 'x':
    case 'X':
      status_flags->spec_int = true;

      if ((*format) == 'u') status_flags->sharp = false;

      int base = *format == 'o' ? 8 : *format == 'u' ? 10 : 16;
      bool high_reg = *format == 'X' ? true : false;

      if (l_flag) {
        out_str = int_to_8_10_16(va_arg(args, unsigned long int), base,
                                 high_reg, status_flags->sharp);
      } else
        out_str = int_to_8_10_16(va_arg(args, unsigned int), base, high_reg,
                                 status_flags->sharp);

      break;

    case 's':

      if (l_flag) {
        wchar_t *ptr = va_arg(args, wchar_t *);
        int i = 0;
        do {
          i++;
        } while (ptr[i] != 0);
        out_str = malloc(i + 5);
        i = 0;
        do {
          out_str[i] = ptr[i];
          i++;
        } while (ptr[i] != '\0');
        out_str[i] = '\0';
        if (*precision != -1) {
          out_str[*precision] = '\0';
        }

      } else {
        char *ptr = va_arg(args, char *);
        out_str = malloc(s21_strlen(ptr) + 2);
        out_str[0] = '\0';

        int len =
            (*precision) == -1 ? (int)((s21_strlen(ptr)) + 2) : (*precision);
        s21_strncat(out_str, ptr, len);
      }

      status_flags->plus = false;
      status_flags->space = false;
      status_flags->nul = false;
      *precision = -1;
      break;

    case 'p':;
      long int pointer = (long int)(uintptr_t)va_arg(args, void *);
      out_str = int_to_8_10_16(pointer, 16, false, true);
      break;

    case 'n':
      out_str = s21_NULL;
      int *count_prnt_sym = va_arg(args, int *);
      *count_prnt_sym = s21_strlen(end_str);

      break;

    case '%':
      out_str = malloc(2);
      out_str[0] = '%';
      out_str[1] = '\0';
      status_flags->plus = false;
      status_flags->space = false;
      status_flags->nul = false;
      *precision = -1;
      break;

    default:
      (*shift)--;
      out_str = s21_NULL;
      break;
  }
  (*shift)++;

  return out_str;
}

char *out_str_formatting(char *str, struct flags status_flags, int width,
                         int precision) {
  int len_str = s21_strlen(str);
  int size = width > precision     ? width > len_str ? width : len_str
             : precision > len_str ? precision
                                   : len_str;
  char *out_str = malloc(size + 5);
  out_str[0] = '\0';

  char sym_str[size + 2];

  sym_str[0] = '\0';
  int sym_index = 0;

  if (status_flags.spec_float || status_flags.spec_int) {
    int have_znak = 0;
    if (str[0] == '-') {
      sym_str[0] = '-';
      sym_index++;
      have_znak = 1;
    } else if (status_flags.plus) {
      sym_str[sym_index] = '+';
      sym_index++;
    } else if (status_flags.space) {
      sym_str[sym_index] = ' ';
      sym_index++;
    }
    sym_str[sym_index] = '\0';

    if (status_flags.spec_int) {
      int len = s21_strlen(str);
      len = have_znak == 0 ? len : len - 1;
      for (int i = len; i < precision; i++) {
        sym_str[sym_index] = '0';
        sym_index++;
        sym_str[sym_index] = '\0';
      }
    }
    if (status_flags.nul) {
      for (; sym_index < width - len_str + have_znak; sym_index++) {
        sym_str[sym_index] = '0';
        sym_str[sym_index + 1] = '\0';
      }
    }
    s21_strncat(sym_str, str + have_znak, size + 5);
  } else {
    s21_strncat(sym_str, str, size + 5);
  }
  free(str);

  int len = s21_strlen(sym_str);
  char wdth_str[size + 2];
  wdth_str[0] = '\0';
  for (int i = 0; i < width - len; i++) {
    wdth_str[i] = ' ';
    wdth_str[i + 1] = '\0';
  }
  if (status_flags.hyphen) {
    s21_strncat(sym_str, wdth_str, size + 5);
    s21_strncat(out_str, sym_str, size + 5);
  } else {
    s21_strncat(wdth_str, sym_str, len + 5);
    s21_strncat(out_str, wdth_str, size + 5);
  }
  return out_str;
}

char *from_int_to_string(long long int src) {
  long long int sing, i = 1;
  if ((sing = src) < 0) {
    src = -src;
  }
  char *out = malloc(25);
  out[0] = src % 10 + '0';
  for (; (src /= 10) > 0; i++) {
    out[i] = src % 10 + '0';
  }
  if (sing < 0) {
    out[i++] = '-';
  }
  out[i] = '\0';
  reverse(out);
  return out;
}

void reverse(char *out) {
  int j, i;
  char tmp;
  for (i = 0, j = s21_strlen(out) - 1; i < j; i++, j--) {
    tmp = out[i];
    out[i] = out[j];
    out[j] = tmp;
  }
}

char *from_double_to_str(long double src, int precision, bool have_sharp) {
  char *out = malloc(25 + precision);
  out[0] = '\0';
  if (src < 0) {
    out[0] = '-';
    out[1] = '\0';
    src = -src;
  }

  long long int integer = (long long int)src;
  if (precision == 0) integer = (long long int)round(src);
  char *integer_str = from_int_to_string(integer);
  s21_strncat(out, integer_str, 25);
  free(integer_str);

  if (have_sharp || precision != 0) {
    s21_strncat(out, ".", 2);

    if (precision != 0) {
      src = fmod(src, 1.);
      int index = s21_strlen(out);
      bool flag = false;
      for (int i = 0; i < precision; i++) {
        src *= 10;
        integer = src;

        if (integer == 0 && !flag) {
          out[index] = '0';
          out[index + 1] = '\0';
          index++;
        } else {
          flag = true;
        }

        if (flag) {
          src = round(src * pow(10, precision - i - 1));
          integer = src;
          integer_str = from_int_to_string(integer);
          s21_strncat(out, integer_str, precision + 1);
          free(integer_str);
          break;
        }
      }
    }
  }
  return out;
}

char *mant_exp_str(long double src, int precision, bool have_sharp,
                   char E_or_e) {
  int exp = 0;
  while (true) {
    if (fabs((double)src) >= 10) {
      src /= 10.;
      exp++;
    } else if (fabs((double)src) < 1) {
      src *= 10.;
      exp--;
    } else {
      break;
    }
  }
  char *exp_str = from_int_to_string(abs(exp));
  char format_exp_str[5];
  format_exp_str[0] = E_or_e;
  format_exp_str[1] = exp > 0 ? '+' : '-';
  format_exp_str[2] = '\0';

  if (s21_strlen(exp_str) < 2) {
    format_exp_str[2] = '0';
    format_exp_str[3] = '\0';
  }
  s21_strncat(format_exp_str, exp_str, s21_strlen(exp_str));

  char *mant_str = from_double_to_str(src, precision, have_sharp);
  char *out = malloc(15 + precision);
  out[0] = '\0';
  s21_strncat(out, mant_str, precision + 10);
  s21_strncat(out, format_exp_str, 10);
  free(exp_str);
  free(mant_str);
  return out;
}

char *int_to_8_10_16(long long int src, int base, bool high_reg,
                     bool have_sharp) {
  long long int copy_src = (unsigned)src;
  char *out = malloc(30);
  int index = 0;
  do {
    char sym = src % base + '0';
    if (sym > 57) {
      sym += high_reg ? 7 : 39;
    }
    out[index] = sym;
    index++;
    src /= base;
  } while (src != 0);

  if (copy_src != 0 && have_sharp) {
    out[index] = high_reg ? 'X' : 'x';
    out[index + 1] = '0';
    index += 2;
  }

  out[index] = '\0';
  reverse(out);
  return out;
}

char *short_note_gG(long double src, int precision, bool have_sharp,
                    char E_or_e) {
  char *out = malloc(100 + precision);
  out[0] = '\0';

  // округление from -4 to -3 WHEH FIX DOUBLE

  if (precision == 0) precision = 1;

  char *mant_str = mant_exp_str(src, precision - 1, have_sharp, E_or_e);
  int power = (mant_str[s21_strlen(mant_str) - 2] - '0') * 10;
  power += mant_str[s21_strlen(mant_str) - 1] - '0';
  if (mant_str[s21_strlen(mant_str) - 3] == '-') power *= -1;

  if (power < -4 || power >= precision) {
    free(out);
    if (!have_sharp && power > 0) {
      free(mant_str);
      out = mant_exp_str(src, 0, have_sharp, E_or_e);
    } else {
      out = mant_str;
    }

  } else {
    int index = 0;
    int new_index = 0;
    if (mant_str[0] == '-') {
      out[0] = '-';
      index++;
      new_index++;
    }

    for (int i = power; i < 0; i++) {
      out[new_index] = '0';
      new_index++;
    }
    while (mant_str[index] != E_or_e) {
      if (mant_str[index] != '.') {
        out[new_index] = mant_str[index];
        new_index++;
      }
      index++;
    }
    free(mant_str);
    out[new_index] = '\0';
    char *outout = malloc(100 + precision);
    if (power < 1) {
      power = 0;
    }
    for (int i = 0, j = 0; j < new_index + 1; i++, j++) {
      if (power == j - 1) {
        outout[i] = '.';
        i++;
      }
      outout[i] = out[j];
    }
    outout[new_index + 1] = '\0';
    free(out);
    out = outout;
    while (!have_sharp) {
      if (out[s21_strlen(out) - 1] == '0') {
        out[s21_strlen(out) - 1] = '\0';
      } else {
        break;
      }
    }
  }
  return out;
}
