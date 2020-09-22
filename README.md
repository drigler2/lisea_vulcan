# about lisea vulcan

Vulcan's task in the lisea ecosystem is to provide unique and mostly
serial ID-s. Vulcan should do this extremely efficiently...

In comparison to a Spring boot application; it's like comparing a
great race car to a F1 car designed to do only the casino turn in spring of
'95 in Monte-Carlo.

Currently, Vulcan has throughput of 12 req/s on my PC, I hope this
will eventually be improved upon, I will also put up more info on this
in the future.

Vulcan is based on twitter snowflake service which was then
implemented by Dwayn Matthies, his project has great documentation and
implementation so I've used his ideas, slightly modifying them to live
inside a http server.

As for the server part, I used boost::asio example project (this was my first
asio project), I mostly used the example code as a template, modifying
it to fit inside my project.

### TODOs
generalise building responses, create some request parser selection
stuff, also, the server will brake after completing processing of a
very high load, the ID's seem to be negative in the morning,
externalise config for region/workerId, etc...

### links
* [Twitter snowflake](https://github.com/twitter-archive/snowflake)
* [Snowflaked by Dwayn Matthies](https://github.com/dwayn/snowflaked)
* [boost::asio examples](https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio/examples.html)

LocalWords:  lisea
