import { Temperatura } from "./temperatura.entity";
import { Injectable } from "@nestjs/common";
import { InjectModel } from "@nestjs/sequelize";

@Injectable()
export class TemperaturaService {
  constructor(@InjectModel(Temperatura) private readonly temperaturaModel: typeof Temperatura) {
  }

  async getTemperatura(): Promise<Temperatura[]> {
    return this.temperaturaModel.findAll();
  }

  async createTemperatura(body: Temperatura): Promise<Temperatura> {
    return this.temperaturaModel.create({
      temperatura: body.temperatura,
      umidade: body.umidade,
    });
  }

  async getLastTemperatura(): Promise<Temperatura> {
    return this.temperaturaModel.findOne({order: [["id", "DESC"]]});
  }

  async getLastsTemperatura(limit: number): Promise<Temperatura[]> {
    return this.temperaturaModel.findAll({order: [["id", "DESC"]], limit: limit});
  }
}
