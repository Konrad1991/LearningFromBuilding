# Kronecker product: 
# The Kronecker product of two matrices is a larger matrix obtained by
# taking all possible products of elements from matrix a with matrix b.
kron <- function(a, b) {
  c <- list()
  counter <- 1
  for(i in 1:nrow(a)) {
    res <- lapply(a[i, ], function(x) x*b)
    res <- do.call(cbind, res)
    c[[counter]] <- res
    counter <- counter + 1
  }
  c <- do.call(rbind, c)
  return(c)
}

# Example 1
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8), nrow=2, ncol=2)
c <- kron(a, b)
stopifnot(c == a%x%b)

# Example 2
a <- matrix(c(1,2,3,4), nrow=2, ncol=2)
b <- matrix(c(5,6,7,8,9,10), nrow=2, ncol=3)
c <- kron(a, b)
stopifnot(c == a%x%b)

# Example 3
a <- matrix(c(1,2,3,4,5,6), nrow=2, ncol=3)
b <- matrix(c(7,8,9,10,11,12), nrow=3, ncol=2)
c <- kron(a, b)
stopifnot(c == a%x%b)

# Example 4
a <- matrix(c(1,2,3), nrow=1, ncol=3)
b <- matrix(c(4,5,6), nrow=3, ncol=1)
c <- kron(a, b)
stopifnot(c == a%x%b)
