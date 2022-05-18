import {Column, DataType, Model, Table} from "sequelize-typescript";

@Table({
    tableName: "temperaturas"
})
export class Temperatura extends Model<Temperatura> {
    @Column({
        type: DataType.DOUBLE,
        allowNull: false,
    })
    temperatura: number;

    @Column({
        type: DataType.DOUBLE,
        allowNull: false,
    })
    umidade: number;
}
