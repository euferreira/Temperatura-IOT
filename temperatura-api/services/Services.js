const database = require("../models");
const Op = require("sequelize").Op;

class Services {
    constructor(nomeModelo) {
        this.nomeModelo = nomeModelo;
    }

    async findAll(where = {}) {
        return database[this.nomeModelo].findAll({where: {...where}});
    }

    async findOne(where = {}) {
        return database[this.nomeModelo].findOne({where: {...where}});
    }

    async findAndCountAll(where = {}) {
        return database[this.nomeModelo].findAndCountAll({where: {...where}});
    }

    async insert(dados) {
        return database[this.nomeModelo].create(dados);
    }
}

module.exports = Services;
