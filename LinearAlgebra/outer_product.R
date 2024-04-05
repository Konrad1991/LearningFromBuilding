# Outer product: 
# The outer product of two vectors is a matrix that represents the product (or f)
# of each element of one vector with each element of the other vector.
a <- c(2, 5, 6, 4)
b <- c(4, 3, 7)
out <- function(a, b, f = NULL) {
  if(is.null(f)) {
    f <- `*`
  } else {
    stopifnot(is.function(f))
  }
  stopifnot(dim(a) == dim(b))
  res <- NULL
  if(is.null(dim(a))) {
    res <- array(0, dim = c(length(a), length(b)))
  } else {
    res <- array(0, dim = c(dim(a), dim(b)) )  
  }
  counter <- 1
  for(i in 1:length(b)) { # cols
    temp_b <- b[i]
    for(j in 1:length(a)) { # rows
      res[counter] <- f(a[j], temp_b)
      counter <- counter + 1
    }
  }
  
  return(res)
}

outer(a, b, `^`)
outer(a, b, \(a, b) {paste0(a, "^", b)})
out(a, b, `^`)
out(a, b, \(a, b) {paste0(a, "^", b)})
stopifnot( a%o%b == out(a, b))

a <- array(1:36, dim = c(3, 3, 4))
b <- array( (1:36) + 3.14, dim = c(3, 3, 4))
stopifnot( a%o%b == out(a, b))