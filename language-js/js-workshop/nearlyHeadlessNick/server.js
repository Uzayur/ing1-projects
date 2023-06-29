"use strict";

const Fastify = require("fastify");
const fastifyStatic = require("@fastify/static");

(async () => {
  let server = Fastify();
  server.register(fastifyStatic, {
    root: `${__dirname}`,
  });

  await server.listen(5050, "localhost");
})();
