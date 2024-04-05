# Inner product:
# The inner product of two vectors is a scalar that measures the angle between them.
# It is also known as the dot product.
inner <- function(a, b) {
  stopifnot(dim(a) == dim(b))
  
  vec_vec_inner <- function(a, b) {
    stopifnot(length(a) == length(b))
    res <- 0
    for(i in 1:length(a)) {
      res <- res + a[i]*b[i]
    }
    res
  }
  
  rec <- function(a, b, env) {
    if( is.null(dim(a)) && is.null(dim(b)) ) {
      res <- vec_vec_inner(a, b)
      env$res <- c(env$res, res)
      return(res)
    } else {
      l <- length(dim(a))
      last_dim <- dim(a)[l]
      trash <- lapply(seq(last_dim), function(x) {
        indices <- rep(alist(,)[1], l)
        indices[l] <- x
        a <- do.call(`[`, c(list(a), indices))
        b <- do.call(`[`, c(list(b), indices))
        ret <- rec(a, b, env)
        return(0)
      })
    }
  }
  
  env <- new.env()
  env$res <- NULL
  if(is.null(dim(a))) {
    env$res <- vec_vec_inner(a, b)
  } else {
    l <- dim(a)[length(dim(a))]
    for(i in 1:l) {
      rec(a, b, env)
    }
  }
  
  if(is.null(dim(a))) {
    return(env$res)
  } else {
    return(sum(env$res)/dim(a)[length(dim(a))] )
  }
  
}

a <- c(2, 5, 6)
b <- c(4, 3, 2)
stopifnot( a%*%b == inner(a, b))

a <- array(1:6, dim = c(3, 2))
b <- array(7:12, dim = c(3, 2))
stopifnot( 217 == inner(a, b))

a <- array(1:36, dim = c(3, 3, 4))
b <- array( (1:36) + 3.14, dim = c(3, 3, 4))
stopifnot( a%*%b == inner(a, b))