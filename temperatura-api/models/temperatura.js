'use strict';
const {
  Model
} = require('sequelize');
module.exports = (sequelize, DataTypes) => {
  class Temperatura extends Model {
    /**
     * Helper method for defining associations.
     * This method is not a part of Sequelize lifecycle.
     * The `models/index` file will call this method automatically.
     */
    static associate(models) {
      // define association here
    }
  }
  Temperatura.init({
    temperatura: DataTypes.DOUBLE,
    umidade: DataTypes.DOUBLE
  }, {
    sequelize,
    modelName: 'Temperatura',
  });
  return Temperatura;
};