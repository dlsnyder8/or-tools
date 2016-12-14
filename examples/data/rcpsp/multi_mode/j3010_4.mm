************************************************************************
file with basedata            : mf10_.bas
initial value random generator: 826443769
************************************************************************
projects                      :  1
jobs (incl. supersource/sink ):  32
horizon                       :  237
RESOURCES
  - renewable                 :  2   R
  - nonrenewable              :  2   N
  - doubly constrained        :  0   D
************************************************************************
PROJECT INFORMATION:
pronr.  #jobs rel.date duedate tardcost  MPM-Time
    1     30      0       36       10       36
************************************************************************
PRECEDENCE RELATIONS:
jobnr.    #modes  #successors   successors
   1        1          3           2   3   4
   2        3          2           8  27
   3        3          2           6   9
   4        3          1           5
   5        3          2          14  20
   6        3          3           7  12  13
   7        3          1          17
   8        3          2          19  20
   9        3          3          10  11  18
  10        3          3          12  14  22
  11        3          3          12  23  26
  12        3          3          21  28  29
  13        3          3          16  17  26
  14        3          1          15
  15        3          3          16  17  28
  16        3          1          27
  17        3          2          19  25
  18        3          3          22  25  28
  19        3          2          23  24
  20        3          3          22  24  25
  21        3          1          27
  22        3          2          30  31
  23        3          1          31
  24        3          1          31
  25        3          1          29
  26        3          1          29
  27        3          1          30
  28        3          1          30
  29        3          1          32
  30        3          1          32
  31        3          1          32
  32        1          0        
************************************************************************
REQUESTS/DURATIONS:
jobnr. mode duration  R 1  R 2  N 1  N 2
------------------------------------------------------------------------
  1      1     0       0    0    0    0
  2      1     3       8    0    0    3
         2     8       6    0    0    2
         3    10       0    5    0    2
  3      1     3       6    0    6    0
         2     4       0    6    0    5
         3     6       4    0    6    0
  4      1     1       9    0    0    3
         2     3       7    0    0    1
         3     6       0   10    9    0
  5      1     3       6    0    9    0
         2     8       0    5    6    0
         3     9       5    0    6    0
  6      1     2       0    5    4    0
         2     6       7    0    2    0
         3    10       5    0    0    8
  7      1     4       7    0    0    8
         2     7       6    0    8    0
         3     9       6    0    7    0
  8      1     3       0    7    9    0
         2     7       9    0    5    0
         3     7       0    6    0    6
  9      1     5       0    8    7    0
         2    10       0    7    0    5
         3    10       6    0    5    0
 10      1     8       0    5    0    3
         2     8       0    4    0    4
         3    10       5    0    6    0
 11      1     1       0    2    5    0
         2     5       8    0    4    0
         3     7       6    0    4    0
 12      1     8       0   10    0    5
         2     9       0    7    5    0
         3    10       0    4    0    2
 13      1     2       6    0    0    6
         2     3       5    0    0    4
         3     5       5    0    8    0
 14      1     3       0    6    0    5
         2     8       3    0    7    0
         3     8       4    0    0    1
 15      1     2       4    0    3    0
         2     3       0    3    2    0
         3     7       3    0    0    3
 16      1     4       0    4    0    6
         2     4       3    0    0    6
         3     8       0    4    0    5
 17      1     7       0    5    6    0
         2     7       0    5    0    4
         3     9       0    1    0    3
 18      1     4       0    5    0    6
         2     7       3    0   10    0
         3    10       2    0   10    0
 19      1     1       8    0    7    0
         2     3       0    3    5    0
         3     6       6    0    3    0
 20      1     6       9    0    3    0
         2     6       0    4    0    9
         3     7       0    4    0    2
 21      1     1       4    0    0    6
         2    10       0   10    0    5
         3    10       3    0    5    0
 22      1     1       0    4    0    7
         2     3       9    0    5    0
         3     5       9    0    0    7
 23      1     1       3    0    2    0
         2     6       0    8    0    5
         3     7       3    0    0    4
 24      1     1       0    4    0    8
         2     2       7    0    2    0
         3     6       4    0    0    8
 25      1     7       4    0    0    3
         2     7       1    0   10    0
         3     8       0    8    0    3
 26      1     3       0    9    0   10
         2     5       7    0    5    0
         3     8       6    0    0    7
 27      1     1      10    0    6    0
         2     4       0    7    0    8
         3     4       9    0    0    4
 28      1     3       0    9    7    0
         2     8       0    9    0    8
         3     8       7    0    0    4
 29      1     1       4    0    0    8
         2     6       0    4    0    7
         3     8       0    1    0    4
 30      1     8       0    4    0    5
         2     8       3    0    8    0
         3     9       2    0    0    6
 31      1     1       0    5    0    5
         2     7       0    4    0    3
         3    10       0    3    8    0
 32      1     0       0    0    0    0
************************************************************************
RESOURCEAVAILABILITIES:
  R 1  R 2  N 1  N 2
   17   18   92   86
************************************************************************