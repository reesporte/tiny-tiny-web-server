# tiny tiny web server

i made a tiny tiny web server to learn about how web servers work

it responds to all requests with one response

obviously not for production use 

## to use

make sure _localhost:8080_ is not already in use, then  

```
$ make run
$ curl localhost:8080
```

you should get something like this
```
<html>
    <head>
        <title>IT WORKS</title>
    </head>
    <body>
        <h1>my tiny server works</h1>
    </body>
</html>
```
