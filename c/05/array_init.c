char inferred_size[] = "abcd"; /* size: 5 (includes null terminator '\0') */
                               /* elements: ['a', 'b', 'c', 'd', '\0'] */

int zero_initialized[5] = { 0 }; /* size: 5 */
                                 /* elements: [0, 0, 0, 0, 0] */

int fully_initialized[5] = { 2, 4, 6, 8, 10 }; /* size: 5 */
                                               /* elements: [2, 4, 6, 8, 10] */
