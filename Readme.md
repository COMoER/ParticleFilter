# Particle Filter for Radar

Suppose particles are ![1](http://latex.codecogs.com/svg.latex?\\{x^{(i)}\\}_{i=1}^{N_s}) 

- Algorithm

> Initialize the state in all locations of the grids as
>
> ![2](http://latex.codecogs.com/svg.latex?\\{x_0^{(i)},w_0^{(i)}\\}) , 
> ![3](http://latex.codecogs.com/svg.latex?w_0^{(i)}=\\frac{1}{N_s},\\forall{i})
> ![4](http://latex.codecogs.com/svg.latex?x_0^{(i)}=[x,y,\\dot{x},\\dot{y}]^T)
>
> for t = 1 to ![2](http://latex.codecogs.com/svg.latex?\\infty)
>
> > re-sample the particle ![2](http://latex.codecogs.com/svg.latex?\\{x_{t-1}^{*(j)}\\}_{j=1}^{N_s}) based on the weights ![2](http://latex.codecogs.com/svg.latex?\\{w_{t-1}^{(i)}\\})
> >
> > Using prediction model ![2](http://latex.codecogs.com/svg.latex?x_t=f(x_{t-1})+w_t)  to sample ![2](http://latex.codecogs.com/svg.latex?\\{x_t^{(i)}\\}_{i=1}^{N_s}) with 
> ![2](http://latex.codecogs.com/svg.latex?\\{x_{t-1}^{*(i)}\\}_{i=1}^{N_s}) 
> >
> > Using observation model to assign weight for each particles ![2](http://latex.codecogs.com/svg.latex?w_t^{i}=\\Pr{(z_t|x_t^{(i)})}=\mathcal{N}(x_t^{(i)},\sigma^2)(z_t))
> >
> > Normalize ![2](http://latex.codecogs.com/svg.latex?\\{w_t^{i}\\}_{i=1}^{N_s})
> >
> > output the estimation ![2](http://latex.codecogs.com/svg.latex?\\hat{x_t}=\sum_{i=1}^{N_s}w_t^{i}x_t^{(i)})
>
> end for

