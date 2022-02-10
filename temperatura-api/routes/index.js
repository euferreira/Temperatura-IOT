module.exports = (app) => {
    const bodyParser = require("body-parser");
    const temperatura = require("./temperatura.route");
    app.use(bodyParser.json(), temperatura);
}
