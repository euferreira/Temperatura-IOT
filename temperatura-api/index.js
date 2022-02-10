const app = require('express')();
require("./routes")(app);

app.listen(3000);

module.exports = app;
