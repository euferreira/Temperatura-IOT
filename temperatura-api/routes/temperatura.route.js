const router = require('express').Router();
const TemperaturaController = require("../controllers/TemperaturaController");

router.post('/api/temperatura', TemperaturaController.insert);
router.get('/api/temperatura', TemperaturaController.get).get("/api/temperatura/count", TemperaturaController.getAndCount);

module.exports = router;
