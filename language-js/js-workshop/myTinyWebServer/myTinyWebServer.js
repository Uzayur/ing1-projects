function myTinyWebServer(port, host)
{
    const http = require ("http");



    const requestListener = function (req, res) {
        res.writeHead(200, { 'Content-Type': 'application/json' });

        if (req.url === "/")
            {

                if (req.method === "POST")
                {
                    let str = '';

                    req.on('data', (chunk) => { str += chunk; });
                    req.on('end', () => {
                    try {

                        const parsedData = JSON.parse(str);//on parse le body
                        str = JSON.stringify(parsedData);
                        console.log(parsedData);
                        res.end(str);
                    } catch (e) {
                        res.end(JSON.stringify({ message: str }));
                    }
                });
            }
                else if (req.method === "GET")
                    res.end(JSON.stringify({message: "Hello World!"}, null, '\t'));
            }

        else if (req.url === "/about" && req.method === "GET")
            res.end(JSON.stringify({message: "About page"}, null, '\t'));

        else if (req.url === "/articles" && req.method === "GET")
        {
                const config = require('./data.json');
                str = JSON.stringify(config);
                res.end(str);

                if (res.body != config)
                        return;
        }
        else
            res.end(JSON.stringify({message: "Not  the found"}));

        console.log(req);
    };


    const server = http.createServer(requestListener);

    server.listen(port, host);
    console.log(`Server running at in of http://${host}:${port}/`);
        }

    let server = myTinyWebServer(8080, "localhost");

module.exports = {
myTinyWebServer
}
