const {TemperaturaService} = require("../services");
const temperaturaService = new TemperaturaService();

class TemperaturaController {
    static async get(req, res) {
        try {
            const all = await temperaturaService.findAll();
            return all.length > 0 ? res.status(200).json(all) : res.status(204);
        }
        catch (e) {
            return res.status(500).json({send: e.message});
        }
    }

    static async getAndCount(req, res) {
        try {
            const all = await temperaturaService.findAndCountAll();
            return res.status(200).json(all);
        }
        catch (e) {
            return res.status(500).json({send: e.message});
        }
    }

    static async insert(req, res) {
        try {
            console.log(req.body);
            const temp = await temperaturaService.insert(req.body);
            return temp !== null ? res.status(201).json(temp) : res.status(400).json({send: "Erro na inserção!"});
        }
        catch (e) {
            return res.status(500).json({send: e.message});
        }
    }
}

module.exports = TemperaturaController;
