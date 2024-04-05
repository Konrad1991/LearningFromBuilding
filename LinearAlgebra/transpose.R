# Transpose:
# The transpose of a matrix is obtained by swapping its rows and columns.
transpose <- function(a) {
  if(is.null(dim(a))) {
    return(matrix(a, nrow = 1, ncol = length(a)))
  } else {
    ret <- apply(a, 1, function(x) {
      return(x)
    })
    return(ret)
  }
}

a <- c(2, 5, 6) # column vector
stopifnot( t(a) == transpose(a))

a <- array(1:6, dim = c(3, 2))
stopifnot( t(a) == transpose(a))
