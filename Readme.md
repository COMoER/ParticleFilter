# Particle Filter for Radar

Suppose particles are ${x^{(i)}}_{i=1}^{N_s}$ 

- Algorithm

> Initialize the state in all locations of the grids as
>
> $\{x_0^{(i)},w_0^{(i)}\}$ , $w_0^{(i)} =\frac{1}{N_s}\forall i$        $x_0^{(i)} = [x,y,\dot x,\dot y]^T$
>
> for t = 1 to $\infty$
>
> > re-sample the particle $\{x_{t-1}^{*(j)}\}_{j=1}^{N_s}$ based on the weights ${w_{t-1}^{(i)}}$
> >
> > Using prediction model $x_t = f(x_{t-1})+w_t$ to sample $\{x_t^{(i)}\}_{i=1}^{N_s}$ with $\{x_{t-1}^{*(i)}\}_{i=1}^{N_s}$ 
> >
> > Using observation model to assign weight for each particles $w_t^{i} = \Pr(z_t|x_t^{(i)})=\mathcal{N}(x_t^{(i)},\sigma^2)(z_t)$
> >
> > Normalize $\{w_t^{i}\}_{i=1}^{N_s}$
> >
> > output the estimation $\hat x_t = \sum_{i=1}^{N_s}w_t^{i}x_t^{(i)}$
>
> end for

