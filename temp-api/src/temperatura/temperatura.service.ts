import {Temperatura} from "./temperatura.entity";
import {Injectable} from "@nestjs/common";
import {InjectModel} from "@nestjs/sequelize";

@Injectable()
export class TemperaturaService {
    constructor(@InjectModel(Temperatura) private readonly temperaturaModel: typeof Temperatura) {
    }

    async getTemperatura(): Promise<Temperatura[]> {
        return this.temperaturaModel.findAll();
    }

    async createTemperatura(body: Temperatura): Promise<Temperatura> {
        return this.temperaturaModel.create(body);
    }
}

export interface Temperaturas {
    temperatura( body: Temperatura): Promise<Temperatura>;
    umidade( body: Temperatura): Promise<Temperatura>;
}

@Injectable()
export class Teste implements Temperaturas {
    temperatura( body: Temperatura): Promise<Temperatura> {
        return new Promise(resolve => {
            resolve(body);
        });
    }

    umidade( body: Temperatura): Promise<Temperatura> {
        return new Promise(resolve => {
            resolve(body);
        });
    }
}
