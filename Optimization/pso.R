
# particle swarm optimization
pso <- function(lb, ub, loss, ngen, npop, global = FALSE) {
	stopifnot(length(lb) == length(ub))
	npar = length(lb)
	swarm <- matrix(0, nrow = npop, ncol = npar)
	v <- matrix(0, nrow = npop, ncol = npar)
	swarm_bests <- numeric(length(npop))
	swarm_errors <- numeric(length(npop))
	initial_cog = 2.5
	final_cog = 0.5
	initial_soc = 0.5
	final_soc = 2.5
	w = 0.5
	w_max = 0.9
	w_min = 0.4
	for(i in seq(npop)) {
		swarm[i, ] <-  runif(npar, min = lb, max = ub)
		swarm_errors[i] <- loss(swarm[i, ])
		swarm_bests[i] <- swarm_errors[i]
	}	
	global_best <- which.min(swarm_bests)
	global_best_vec <- swarm[global_best, ]
	global_best_error <- swarm_bests[global_best]
	swarm_best_params <- swarm
	K <- 3
	
	calc_neighberhood <- function() {
		neighberhood <- matrix(0L, ncol = K, nrow = npop)	
		for(i in seq(npop)) {
			nneighbour <- sample(1:K, 1)
			neighbours <- sample(1:npop, nneighbour)
			if(length(neighbours) < K) {
				diff = K - length(neighbours)
				neighbours <- c(neighbours, rep(NA, diff))
			}
			neighberhood[i, ] <- neighbours
		}
		neighberhood
	}
	neighberhood <- calc_neighberhood()
	convergence_check <- 0
	
	iter <- 1
	while(iter < ngen) {
		if (iter == 1 || convergence_check != 0) {
			neighberhood <- calc_neighberhood()
	    }

	    w <- w_max - iter * (w_max - w_min) / ngen;
	    cog <- initial_cog - (initial_cog - final_cog) * (iter + 1) / ngen;
	    soc <- initial_soc - (initial_soc - final_soc) * (iter + 1) / ngen;

		for(i in seq(npop)) {
			current_neighberhood <- neighberhood[i, ]
			current_neighberhood <- current_neighberhood[!is.na(current_neighberhood)]
			local_best <- which.min(swarm_bests[current_neighberhood])
			local_best <- current_neighberhood[local_best]
			local_best_vec <- swarm[local_best, ]

			if(global == TRUE) {
				local_best_vec <- swarm[global_best, ]	
			}
			
			v[i, ] <- w * v[i, ] + 
					  cog * runif(1) * (swarm_best_params[i, ] - swarm[i, ]) +
					  soc * runif(1) * (local_best_vec - swarm[i, ])
			swarm[i, ] <- swarm[i, ] + v[i, ]
			error <- loss(swarm[i, ])
			if(!is.infinite(error) & !is.na(error) &
				error < swarm_bests[i]) {
				swarm_bests[i] <- error
				swarm_best_params[i, ] <- swarm[i, ]
			}
			if(!is.infinite(error) & !is.na(error) &
			error < global_best_error) {
				global_best <- i
				global_best_vec <- swarm[i, ]
				global_best_error <- error
				convergence_check <- 0
			}
			convergence_check <- convergence_check + 1
		}
	    
	    iter <- iter + 1

		if(iter %% 50 == 0) {
			print(iter)
			print(global_best_vec)
			print(global_best_error)
		}
	    
	}
	return(global_best_vec)	
}

lb <- c(-2, -2)
ub <- c(2, 2)
ngen = 10000
npop = 80
# zero at 1, 1
loss <- function(x) {(1 - x[1])^2 + 100*(x[2]- x[1]^2)^2}
res <- pso(lb, ub, loss, ngen, npop, TRUE)
loss(res)