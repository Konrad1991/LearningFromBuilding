# Matrix multiplication
# Matrix multiplication is a binary operation that takes two matrices as input 
# and produces a new matrix as output. It is associative, but not commutative.

# a is a m x n matrix
# b is a n x p matrix
# result c is a m x p matrix 
mul_naiv <- function(a, b) {
  stopifnot(dim(a)[2] == dim(b)[1])
  c <- matrix(0, nrow = nrow(a), ncol = ncol(b))
  
  vec_vec_inner <- function(a, b) {
    stopifnot(length(a) == length(b))
    res <- 0
    for(i in 1:length(a)) {
      res <- res + a[i]*b[i]
    }
    res
  }
  
  a_row <- NULL
  b_col <- NULL
  for(i in 1:nrow(a)) {
    a_row <- a[i, ]
    for(j in 1:ncol(b)) {
      b_col <- b[, j]
      c[i, j] <- vec_vec_inner(a_row, b_col)
    }
  }
  
  return(c)
}

# Example 1
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8), nrow=2, ncol=2)
c <- mul_naiv(a, b)
stopifnot(c == a%*%b)

# Example 2
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8,9,10), nrow=2, ncol=3)
c <- mul_naiv(a, b)
stopifnot(c == a%*%b)

# Example 3
a <- matrix(c(1,2,3,4,5,6), nrow=2, ncol=3)
b <- matrix(c(7,8,9,10,11,12), nrow=3, ncol=2)
c <- mul_naiv(a, b)
stopifnot(c == a%*%b)

# Example 4
a <- matrix(c(1,2,3), nrow=1, ncol=3)
b <- matrix(c(4,5,6), nrow=3, ncol=1)
c <- mul_naiv(a, b)
stopifnot(c == a%*%b)


# https://gregorygundersen.com/blog/2020/07/17/matmul/
# http://mlwiki.org/index.php/Matrix-Matrix_Multiplication
# a is a m x n matrix
# b is a n x p matrix
# result c is a m x p  matrix 
# C[i,j] = sum(A[i,k] * B[k,j]), k=1 to n
# C = sum_{k=1}^{n} A[,k] %o% B[k,]
mul <- function(a, b) {
  stopifnot(dim(a)[2] == dim(b)[1])
  c <- matrix(0, nrow = nrow(a), ncol = ncol(b))
  for(i in 1:ncol(a)) {
    c <- c + outer(a[, i], b[i, ])
  }
  return(c)
}

# Example 1
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8), nrow=2, ncol=2)
c <- mul(a, b)
stopifnot(c == a%*%b)

# Example 2
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8,9,10), nrow=2, ncol=3)
c <- mul(a, b)
stopifnot(c == a%*%b)

# Example 3
a <- matrix(c(1,2,3,4,5,6), nrow=2, ncol=3)
b <- matrix(c(7,8,9,10,11,12), nrow=3, ncol=2)
c <- mul(a, b)
stopifnot(c == a%*%b)

# Example 4
a <- matrix(c(1,2,3), nrow=1, ncol=3)
b <- matrix(c(4,5,6), nrow=3, ncol=1)
c <- mul(a, b)
stopifnot(c == a%*%b)
